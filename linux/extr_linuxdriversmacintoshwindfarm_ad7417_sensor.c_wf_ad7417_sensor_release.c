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
struct wf_sensor {int /*<<< orphan*/  name; struct wf_ad7417_priv* priv; } ;
struct wf_ad7417_priv {int /*<<< orphan*/  ref; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kref_put (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wf_ad7417_release ; 

__attribute__((used)) static void wf_ad7417_sensor_release(struct wf_sensor *sr)
{
	struct wf_ad7417_priv *pv = sr->priv;

	kfree(sr->name);
	kref_put(&pv->ref, wf_ad7417_release);
}