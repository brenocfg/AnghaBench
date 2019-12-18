#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  vd ;
typedef  int u32 ;
struct update_props_workarea {int /*<<< orphan*/  nprops; int /*<<< orphan*/  phandle; } ;
struct device_node {int dummy; } ;
typedef  int /*<<< orphan*/  s32 ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int EINVAL ; 
 int ENOENT ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  RTAS_DATA_BUF_SIZE ; 
 int RTAS_UNKNOWN_SERVICE ; 
 int be32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (char*) ; 
 char* kzalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct device_node* of_find_node_by_phandle (int) ; 
 int /*<<< orphan*/  of_node_put (struct device_node*) ; 
 int /*<<< orphan*/  pr_err (char*,char*,int) ; 
 int rcall (int,char*,int /*<<< orphan*/ ) ; 
 int rtas_token (char*) ; 
 scalar_t__ strlen (char*) ; 
 int update_property (struct device_node*,char*,int,char*) ; 

__attribute__((used)) static int update_node(__be32 phandle, s32 scope)
{
	struct update_props_workarea *upwa;
	struct device_node *dn;
	int i, rc, ret;
	char *prop_data;
	char *buf;
	int token;
	u32 nprops;
	u32 vd;

	token = rtas_token("ibm,update-properties");
	if (token == RTAS_UNKNOWN_SERVICE)
		return -EINVAL;

	buf = kzalloc(RTAS_DATA_BUF_SIZE, GFP_KERNEL);
	if (!buf)
		return -ENOMEM;

	dn = of_find_node_by_phandle(be32_to_cpu(phandle));
	if (!dn) {
		kfree(buf);
		return -ENOENT;
	}

	upwa = (struct update_props_workarea *)&buf[0];
	upwa->phandle = phandle;
	do {
		rc = rcall(token, buf, scope);
		if (rc < 0)
			break;

		prop_data = buf + sizeof(*upwa);
		nprops = be32_to_cpu(upwa->nprops);

		if (*prop_data == 0) {
			prop_data++;
			vd = be32_to_cpu(*(__be32 *)prop_data);
			prop_data += vd + sizeof(vd);
			nprops--;
		}

		for (i = 0; i < nprops; i++) {
			char *prop_name;

			prop_name = prop_data;
			prop_data += strlen(prop_name) + 1;
			vd = be32_to_cpu(*(__be32 *)prop_data);
			prop_data += sizeof(vd);

			if ((vd != 0x00000000) && (vd != 0x80000000)) {
				ret = update_property(dn, prop_name, vd,
						prop_data);
				if (ret)
					pr_err("cxl: Could not update property %s - %i\n",
					       prop_name, ret);

				prop_data += vd;
			}
		}
	} while (rc == 1);

	of_node_put(dn);
	kfree(buf);
	return rc;
}