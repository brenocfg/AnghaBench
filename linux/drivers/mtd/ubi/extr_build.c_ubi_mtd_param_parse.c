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
struct mtd_dev_param {char* name; scalar_t__ vid_hdr_offs; int /*<<< orphan*/  ubi_num; int /*<<< orphan*/  max_beb_per1024; } ;
struct kernel_param {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int MTD_PARAM_LEN_MAX ; 
 int MTD_PARAM_MAX_COUNT ; 
 int /*<<< orphan*/  UBI_DEV_NUM_AUTO ; 
 size_t UBI_MAX_DEVICES ; 
 scalar_t__ bytes_str_to_int (char*) ; 
 int kstrtoint (char*,int,int /*<<< orphan*/ *) ; 
 struct mtd_dev_param* mtd_dev_param ; 
 size_t mtd_devs ; 
 int /*<<< orphan*/  pr_err (char*,...) ; 
 int /*<<< orphan*/  pr_warn (char*) ; 
 int /*<<< orphan*/  strcpy (char*,char const*) ; 
 int strnlen (char const*,int) ; 
 char* strsep (char**,char*) ; 

__attribute__((used)) static int ubi_mtd_param_parse(const char *val, const struct kernel_param *kp)
{
	int i, len;
	struct mtd_dev_param *p;
	char buf[MTD_PARAM_LEN_MAX];
	char *pbuf = &buf[0];
	char *tokens[MTD_PARAM_MAX_COUNT], *token;

	if (!val)
		return -EINVAL;

	if (mtd_devs == UBI_MAX_DEVICES) {
		pr_err("UBI error: too many parameters, max. is %d\n",
		       UBI_MAX_DEVICES);
		return -EINVAL;
	}

	len = strnlen(val, MTD_PARAM_LEN_MAX);
	if (len == MTD_PARAM_LEN_MAX) {
		pr_err("UBI error: parameter \"%s\" is too long, max. is %d\n",
		       val, MTD_PARAM_LEN_MAX);
		return -EINVAL;
	}

	if (len == 0) {
		pr_warn("UBI warning: empty 'mtd=' parameter - ignored\n");
		return 0;
	}

	strcpy(buf, val);

	/* Get rid of the final newline */
	if (buf[len - 1] == '\n')
		buf[len - 1] = '\0';

	for (i = 0; i < MTD_PARAM_MAX_COUNT; i++)
		tokens[i] = strsep(&pbuf, ",");

	if (pbuf) {
		pr_err("UBI error: too many arguments at \"%s\"\n", val);
		return -EINVAL;
	}

	p = &mtd_dev_param[mtd_devs];
	strcpy(&p->name[0], tokens[0]);

	token = tokens[1];
	if (token) {
		p->vid_hdr_offs = bytes_str_to_int(token);

		if (p->vid_hdr_offs < 0)
			return p->vid_hdr_offs;
	}

	token = tokens[2];
	if (token) {
		int err = kstrtoint(token, 10, &p->max_beb_per1024);

		if (err) {
			pr_err("UBI error: bad value for max_beb_per1024 parameter: %s",
			       token);
			return -EINVAL;
		}
	}

	token = tokens[3];
	if (token) {
		int err = kstrtoint(token, 10, &p->ubi_num);

		if (err) {
			pr_err("UBI error: bad value for ubi_num parameter: %s",
			       token);
			return -EINVAL;
		}
	} else
		p->ubi_num = UBI_DEV_NUM_AUTO;

	mtd_devs += 1;
	return 0;
}