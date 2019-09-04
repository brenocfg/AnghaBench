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
struct media_pad {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct media_pad*) ; 

__attribute__((used)) static inline void vimc_pads_cleanup(struct media_pad *pads)
{
	kfree(pads);
}