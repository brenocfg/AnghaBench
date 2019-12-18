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
struct wil6210_priv {int /*<<< orphan*/  mem_lock; int /*<<< orphan*/  status; } ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  down_read_trylock (int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  up_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wil_status_suspended ; 
 int /*<<< orphan*/  wil_status_suspending ; 

int wil_mem_access_lock(struct wil6210_priv *wil)
{
	if (!down_read_trylock(&wil->mem_lock))
		return -EBUSY;

	if (test_bit(wil_status_suspending, wil->status) ||
	    test_bit(wil_status_suspended, wil->status)) {
		up_read(&wil->mem_lock);
		return -EBUSY;
	}

	return 0;
}