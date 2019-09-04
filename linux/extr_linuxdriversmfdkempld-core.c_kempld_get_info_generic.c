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
typedef  int u8 ;
typedef  void* u16 ;
struct TYPE_2__ {int spec_major; scalar_t__ spec_minor; int /*<<< orphan*/  type; int /*<<< orphan*/  number; int /*<<< orphan*/  major; int /*<<< orphan*/  minor; void* buildnr; } ;
struct kempld_device_data {void* feature_mask; TYPE_1__ info; } ;

/* Variables and functions */
 int /*<<< orphan*/  KEMPLD_BUILDNR ; 
 int /*<<< orphan*/  KEMPLD_FEATURE ; 
 int /*<<< orphan*/  KEMPLD_SPEC ; 
 int KEMPLD_SPEC_GET_MAJOR (int) ; 
 scalar_t__ KEMPLD_SPEC_GET_MINOR (int) ; 
 int /*<<< orphan*/  KEMPLD_VERSION ; 
 int /*<<< orphan*/  KEMPLD_VERSION_GET_MAJOR (void*) ; 
 int /*<<< orphan*/  KEMPLD_VERSION_GET_MINOR (void*) ; 
 int /*<<< orphan*/  KEMPLD_VERSION_GET_NUMBER (void*) ; 
 int /*<<< orphan*/  KEMPLD_VERSION_GET_TYPE (void*) ; 
 int /*<<< orphan*/  kempld_get_mutex (struct kempld_device_data*) ; 
 void* kempld_read16 (struct kempld_device_data*,int /*<<< orphan*/ ) ; 
 int kempld_read8 (struct kempld_device_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kempld_release_mutex (struct kempld_device_data*) ; 

__attribute__((used)) static int kempld_get_info_generic(struct kempld_device_data *pld)
{
	u16 version;
	u8 spec;

	kempld_get_mutex(pld);

	version = kempld_read16(pld, KEMPLD_VERSION);
	spec = kempld_read8(pld, KEMPLD_SPEC);
	pld->info.buildnr = kempld_read16(pld, KEMPLD_BUILDNR);

	pld->info.minor = KEMPLD_VERSION_GET_MINOR(version);
	pld->info.major = KEMPLD_VERSION_GET_MAJOR(version);
	pld->info.number = KEMPLD_VERSION_GET_NUMBER(version);
	pld->info.type = KEMPLD_VERSION_GET_TYPE(version);

	if (spec == 0xff) {
		pld->info.spec_minor = 0;
		pld->info.spec_major = 1;
	} else {
		pld->info.spec_minor = KEMPLD_SPEC_GET_MINOR(spec);
		pld->info.spec_major = KEMPLD_SPEC_GET_MAJOR(spec);
	}

	if (pld->info.spec_major > 0)
		pld->feature_mask = kempld_read16(pld, KEMPLD_FEATURE);
	else
		pld->feature_mask = 0;

	kempld_release_mutex(pld);

	return 0;
}