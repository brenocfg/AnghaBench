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
struct pwr_rail_t {int mode; int resistor_count; scalar_t__ config; int /*<<< orphan*/  extdev_id; struct pwr_rail_resistor_t* resistors; } ;
struct pwr_rail_resistor_t {scalar_t__ mohm; int /*<<< orphan*/  enabled; } ;
struct nvkm_subdev {TYPE_1__* device; } ;
struct nvkm_iccsense_sensor {scalar_t__ config; int type; } ;
struct nvkm_iccsense_rail {int (* read ) (struct nvkm_iccsense*,struct nvkm_iccsense_rail*) ;int idx; int /*<<< orphan*/  head; scalar_t__ mohm; struct nvkm_iccsense_sensor* sensor; } ;
struct nvkm_iccsense {int data_valid; int /*<<< orphan*/  rails; int /*<<< orphan*/  power_w_crit; int /*<<< orphan*/  power_w_max; } ;
struct nvkm_bios {int dummy; } ;
struct nvbios_power_budget_entry {int /*<<< orphan*/  max_w; int /*<<< orphan*/  avg_w; } ;
struct nvbios_power_budget {int cap_entry; } ;
struct nvbios_iccsense {int nr_entry; struct pwr_rail_t* rail; } ;
struct TYPE_2__ {struct nvkm_bios* bios; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
#define  NVBIOS_EXTDEV_INA209 130 
#define  NVBIOS_EXTDEV_INA219 129 
#define  NVBIOS_EXTDEV_INA3221 128 
 struct nvkm_iccsense_rail* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ nvbios_iccsense_parse (struct nvkm_bios*,struct nvbios_iccsense*) ; 
 int nvbios_power_budget_entry (struct nvkm_bios*,struct nvbios_power_budget*,int,struct nvbios_power_budget_entry*) ; 
 int nvbios_power_budget_header (struct nvkm_bios*,struct nvbios_power_budget*) ; 
 int /*<<< orphan*/  nvkm_debug (struct nvkm_subdev*,char*,int /*<<< orphan*/ ,int,scalar_t__) ; 
 int /*<<< orphan*/  nvkm_error (struct nvkm_subdev*,char*,int /*<<< orphan*/ ) ; 
 struct nvkm_iccsense* nvkm_iccsense (struct nvkm_subdev*) ; 
 struct nvkm_iccsense_sensor* nvkm_iccsense_get_sensor (struct nvkm_iccsense*,int /*<<< orphan*/ ) ; 
 int nvkm_iccsense_ina209_read (struct nvkm_iccsense*,struct nvkm_iccsense_rail*) ; 
 int nvkm_iccsense_ina219_read (struct nvkm_iccsense*,struct nvkm_iccsense_rail*) ; 
 int nvkm_iccsense_ina3221_read (struct nvkm_iccsense*,struct nvkm_iccsense_rail*) ; 

__attribute__((used)) static int
nvkm_iccsense_oneinit(struct nvkm_subdev *subdev)
{
	struct nvkm_iccsense *iccsense = nvkm_iccsense(subdev);
	struct nvkm_bios *bios = subdev->device->bios;
	struct nvbios_power_budget budget;
	struct nvbios_iccsense stbl;
	int i, ret;

	if (!bios)
		return 0;

	ret = nvbios_power_budget_header(bios, &budget);
	if (!ret && budget.cap_entry != 0xff) {
		struct nvbios_power_budget_entry entry;
		ret = nvbios_power_budget_entry(bios, &budget,
		                                budget.cap_entry, &entry);
		if (!ret) {
			iccsense->power_w_max  = entry.avg_w;
			iccsense->power_w_crit = entry.max_w;
		}
	}

	if (nvbios_iccsense_parse(bios, &stbl) || !stbl.nr_entry)
		return 0;

	iccsense->data_valid = true;
	for (i = 0; i < stbl.nr_entry; ++i) {
		struct pwr_rail_t *pwr_rail = &stbl.rail[i];
		struct nvkm_iccsense_sensor *sensor;
		int r;

		if (pwr_rail->mode != 1 || !pwr_rail->resistor_count)
			continue;

		sensor = nvkm_iccsense_get_sensor(iccsense, pwr_rail->extdev_id);
		if (!sensor)
			continue;

		if (!sensor->config)
			sensor->config = pwr_rail->config;
		else if (sensor->config != pwr_rail->config)
			nvkm_error(subdev, "config mismatch found for extdev %i\n", pwr_rail->extdev_id);

		for (r = 0; r < pwr_rail->resistor_count; ++r) {
			struct nvkm_iccsense_rail *rail;
			struct pwr_rail_resistor_t *res = &pwr_rail->resistors[r];
			int (*read)(struct nvkm_iccsense *,
				    struct nvkm_iccsense_rail *);

			if (!res->mohm || !res->enabled)
				continue;

			switch (sensor->type) {
			case NVBIOS_EXTDEV_INA209:
				read = nvkm_iccsense_ina209_read;
				break;
			case NVBIOS_EXTDEV_INA219:
				read = nvkm_iccsense_ina219_read;
				break;
			case NVBIOS_EXTDEV_INA3221:
				read = nvkm_iccsense_ina3221_read;
				break;
			default:
				continue;
			}

			rail = kmalloc(sizeof(*rail), GFP_KERNEL);
			if (!rail)
				return -ENOMEM;

			rail->read = read;
			rail->sensor = sensor;
			rail->idx = r;
			rail->mohm = res->mohm;
			nvkm_debug(subdev, "create rail for extdev %i: { idx: %i, mohm: %i }\n", pwr_rail->extdev_id, r, rail->mohm);
			list_add_tail(&rail->head, &iccsense->rails);
		}
	}
	return 0;
}