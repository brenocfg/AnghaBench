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
struct wil6210_priv {int /*<<< orphan*/  mem_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  up_read (int /*<<< orphan*/ *) ; 

void wil_mem_access_unlock(struct wil6210_priv *wil)
{
	up_read(&wil->mem_lock);
}