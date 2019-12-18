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
struct dcon_priv {int /*<<< orphan*/  load_time; } ;
typedef  int /*<<< orphan*/  ktime_t ;

/* Variables and functions */
 int NSEC_PER_MSEC ; 
 int /*<<< orphan*/  ktime_get () ; 
 int /*<<< orphan*/  ktime_sub (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ktime_to_ns (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mdelay (int) ; 

__attribute__((used)) static void dcon_load_holdoff(struct dcon_priv *dcon)
{
	ktime_t delta_t, now;

	while (1) {
		now = ktime_get();
		delta_t = ktime_sub(now, dcon->load_time);
		if (ktime_to_ns(delta_t) > NSEC_PER_MSEC * 20)
			break;
		mdelay(4);
	}
}