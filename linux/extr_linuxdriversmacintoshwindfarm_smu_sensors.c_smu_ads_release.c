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
struct wf_sensor {int dummy; } ;
struct smu_ad_sensor {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct smu_ad_sensor*) ; 
 struct smu_ad_sensor* to_smu_ads (struct wf_sensor*) ; 

__attribute__((used)) static void smu_ads_release(struct wf_sensor *sr)
{
	struct smu_ad_sensor *ads = to_smu_ads(sr);

	kfree(ads);
}