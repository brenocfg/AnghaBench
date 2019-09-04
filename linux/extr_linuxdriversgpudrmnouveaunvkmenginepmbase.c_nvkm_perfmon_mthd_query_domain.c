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
typedef  int u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct nvkm_pm {int dummy; } ;
struct nvkm_object {int dummy; } ;
struct nvkm_perfmon {struct nvkm_pm* pm; struct nvkm_object object; } ;
struct nvkm_perfdom {int /*<<< orphan*/  name; } ;
struct nvif_perfmon_query_domain_v0 {int iter; int id; int counter_nr; int /*<<< orphan*/  name; int /*<<< orphan*/  signal_nr; int /*<<< orphan*/  version; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOSYS ; 
 int /*<<< orphan*/  nvif_ioctl (struct nvkm_object*,char*,int /*<<< orphan*/ ,...) ; 
 int nvif_unpack (int,void**,int /*<<< orphan*/ *,struct nvif_perfmon_query_domain_v0,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nvkm_perfdom_count_perfsig (struct nvkm_perfdom*) ; 
 struct nvkm_perfdom* nvkm_perfdom_find (struct nvkm_pm*,int) ; 
 int nvkm_pm_count_perfdom (struct nvkm_pm*) ; 
 int /*<<< orphan*/  strncpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
nvkm_perfmon_mthd_query_domain(struct nvkm_perfmon *perfmon,
			       void *data, u32 size)
{
	union {
		struct nvif_perfmon_query_domain_v0 v0;
	} *args = data;
	struct nvkm_object *object = &perfmon->object;
	struct nvkm_pm *pm = perfmon->pm;
	struct nvkm_perfdom *dom;
	u8 domain_nr;
	int di, ret = -ENOSYS;

	nvif_ioctl(object, "perfmon query domain size %d\n", size);
	if (!(ret = nvif_unpack(ret, &data, &size, args->v0, 0, 0, false))) {
		nvif_ioctl(object, "perfmon domain vers %d iter %02x\n",
			   args->v0.version, args->v0.iter);
		di = (args->v0.iter & 0xff) - 1;
	} else
		return ret;

	domain_nr = nvkm_pm_count_perfdom(pm);
	if (di >= (int)domain_nr)
		return -EINVAL;

	if (di >= 0) {
		dom = nvkm_perfdom_find(pm, di);
		if (dom == NULL)
			return -EINVAL;

		args->v0.id         = di;
		args->v0.signal_nr  = nvkm_perfdom_count_perfsig(dom);
		strncpy(args->v0.name, dom->name, sizeof(args->v0.name) - 1);

		/* Currently only global counters (PCOUNTER) are implemented
		 * but this will be different for local counters (MP). */
		args->v0.counter_nr = 4;
	}

	if (++di < domain_nr) {
		args->v0.iter = ++di;
		return 0;
	}

	args->v0.iter = 0xff;
	return 0;
}