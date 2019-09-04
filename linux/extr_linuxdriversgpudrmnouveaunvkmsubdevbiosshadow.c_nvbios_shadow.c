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
struct shadow {int member_0; scalar_t__ score; scalar_t__ skip; char* data; int /*<<< orphan*/  size; TYPE_1__* func; int /*<<< orphan*/ * member_1; } ;
struct nvkm_subdev {struct nvkm_device* device; } ;
struct nvkm_device {int /*<<< orphan*/  cfgopt; } ;
struct nvkm_bios {char* data; int /*<<< orphan*/  size; struct nvkm_subdev subdev; } ;
struct TYPE_2__ {char* name; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  kfree (char*) ; 
 char* kstrndup (char const*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvbios_acpi_fast ; 
 int /*<<< orphan*/  nvbios_acpi_slow ; 
 int /*<<< orphan*/  nvbios_of ; 
 int /*<<< orphan*/  nvbios_pcirom ; 
 int /*<<< orphan*/  nvbios_platform ; 
 int /*<<< orphan*/  nvbios_ramin ; 
 int /*<<< orphan*/  nvbios_rom ; 
 int /*<<< orphan*/  nvkm_debug (struct nvkm_subdev*,char*,char*) ; 
 int /*<<< orphan*/  nvkm_error (struct nvkm_subdev*,char*,...) ; 
 char* nvkm_stropt (int /*<<< orphan*/ ,char*,int*) ; 
 TYPE_1__ shadow_fw ; 
 scalar_t__ shadow_method (struct nvkm_bios*,struct shadow*,char*) ; 
 int /*<<< orphan*/  strcasecmp (char*,char*) ; 

int
nvbios_shadow(struct nvkm_bios *bios)
{
	struct nvkm_subdev *subdev = &bios->subdev;
	struct nvkm_device *device = subdev->device;
	struct shadow mthds[] = {
		{ 0, &nvbios_of },
		{ 0, &nvbios_ramin },
		{ 0, &nvbios_rom },
		{ 0, &nvbios_acpi_fast },
		{ 4, &nvbios_acpi_slow },
		{ 1, &nvbios_pcirom },
		{ 1, &nvbios_platform },
		{}
	}, *mthd, *best = NULL;
	const char *optarg;
	char *source;
	int optlen;

	/* handle user-specified bios source */
	optarg = nvkm_stropt(device->cfgopt, "NvBios", &optlen);
	source = optarg ? kstrndup(optarg, optlen, GFP_KERNEL) : NULL;
	if (source) {
		/* try to match one of the built-in methods */
		for (mthd = mthds; mthd->func; mthd++) {
			if (mthd->func->name &&
			    !strcasecmp(source, mthd->func->name)) {
				best = mthd;
				if (shadow_method(bios, mthd, NULL))
					break;
			}
		}

		/* otherwise, attempt to load as firmware */
		if (!best && (best = mthd)) {
			mthd->func = &shadow_fw;
			shadow_method(bios, mthd, source);
			mthd->func = NULL;
		}

		if (!best->score) {
			nvkm_error(subdev, "%s invalid\n", source);
			kfree(source);
			source = NULL;
		}
	}

	/* scan all potential bios sources, looking for best image */
	if (!best || !best->score) {
		for (mthd = mthds, best = mthd; mthd->func; mthd++) {
			if (!mthd->skip || best->score < mthd->skip) {
				if (shadow_method(bios, mthd, NULL)) {
					if (mthd->score > best->score)
						best = mthd;
				}
			}
		}
	}

	/* cleanup the ones we didn't use */
	for (mthd = mthds; mthd->func; mthd++) {
		if (mthd != best)
			kfree(mthd->data);
	}

	if (!best->score) {
		nvkm_error(subdev, "unable to locate usable image\n");
		return -EINVAL;
	}

	nvkm_debug(subdev, "using image from %s\n", best->func ?
		   best->func->name : source);
	bios->data = best->data;
	bios->size = best->size;
	kfree(source);
	return 0;
}