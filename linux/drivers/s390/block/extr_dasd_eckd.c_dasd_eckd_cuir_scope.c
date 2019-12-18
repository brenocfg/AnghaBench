#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct dasd_device {TYPE_1__* path; } ;
struct dasd_cuir_message {unsigned long ned_map; int* neq_map; } ;
struct dasd_conf_data {int /*<<< orphan*/  gneq; int /*<<< orphan*/ * neds; } ;
typedef  int __u8 ;
struct TYPE_2__ {struct dasd_conf_data* conf_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  clear_bit (unsigned int,unsigned long*) ; 
 struct dasd_conf_data* dasd_eckd_get_ref_conf (struct dasd_device*,int,struct dasd_cuir_message*) ; 
 int ffs (unsigned long) ; 
 scalar_t__ memcmp (char*,char*,int) ; 

__attribute__((used)) static int dasd_eckd_cuir_scope(struct dasd_device *device, __u8 lpum,
				struct dasd_cuir_message *cuir)
{
	struct dasd_conf_data *ref_conf_data;
	unsigned long bitmask = 0, mask = 0;
	struct dasd_conf_data *conf_data;
	unsigned int pos, path;
	char *ref_gneq, *gneq;
	char *ref_ned, *ned;
	int tbcpm = 0;

	/* if CUIR request does not specify the scope use the path
	   the attention message was presented on */
	if (!cuir->ned_map ||
	    !(cuir->neq_map[0] | cuir->neq_map[1] | cuir->neq_map[2]))
		return lpum;

	/* get reference conf data */
	ref_conf_data = dasd_eckd_get_ref_conf(device, lpum, cuir);
	/* reference ned is determined by ned_map field */
	pos = 8 - ffs(cuir->ned_map);
	ref_ned = (char *)&ref_conf_data->neds[pos];
	ref_gneq = (char *)&ref_conf_data->gneq;
	/* transfer 24 bit neq_map to mask */
	mask = cuir->neq_map[2];
	mask |= cuir->neq_map[1] << 8;
	mask |= cuir->neq_map[0] << 16;

	for (path = 0; path < 8; path++) {
		/* initialise data per path */
		bitmask = mask;
		conf_data = device->path[path].conf_data;
		pos = 8 - ffs(cuir->ned_map);
		ned = (char *) &conf_data->neds[pos];
		/* compare reference ned and per path ned */
		if (memcmp(ref_ned, ned, sizeof(*ned)) != 0)
			continue;
		gneq = (char *)&conf_data->gneq;
		/* compare reference gneq and per_path gneq under
		   24 bit mask where mask bit 0 equals byte 7 of
		   the gneq and mask bit 24 equals byte 31 */
		while (bitmask) {
			pos = ffs(bitmask) - 1;
			if (memcmp(&ref_gneq[31 - pos], &gneq[31 - pos], 1)
			    != 0)
				break;
			clear_bit(pos, &bitmask);
		}
		if (bitmask)
			continue;
		/* device and path match the reference values
		   add path to CUIR scope */
		tbcpm |= 0x80 >> path;
	}
	return tbcpm;
}