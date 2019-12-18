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
struct x25_asy {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  netif_wake_queue (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void x25_asy_unlock(struct x25_asy *sl)
{
	netif_wake_queue(sl->dev);
}