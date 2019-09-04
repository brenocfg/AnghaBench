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
struct wf_sat_sensor {struct wf_sat* sat; } ;
struct wf_sat {int /*<<< orphan*/  ref; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct wf_sat_sensor*) ; 
 int /*<<< orphan*/  kref_put (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wf_sat_release ; 
 struct wf_sat_sensor* wf_to_sat (struct wf_sensor*) ; 

__attribute__((used)) static void wf_sat_sensor_release(struct wf_sensor *sr)
{
	struct wf_sat_sensor *sens = wf_to_sat(sr);
	struct wf_sat *sat = sens->sat;

	kfree(sens);
	kref_put(&sat->ref, wf_sat_release);
}