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
struct tty_struct {int dummy; } ;
struct raw3215_info {scalar_t__ count; int /*<<< orphan*/  tlet; } ;

/* Variables and functions */
 scalar_t__ RAW3215_BUFFER_SIZE ; 
 scalar_t__ RAW3215_MIN_SPACE ; 
 int /*<<< orphan*/  raw3215_mk_write_req (struct raw3215_info*) ; 
 int /*<<< orphan*/  raw3215_try_io (struct raw3215_info*) ; 
 int /*<<< orphan*/  tasklet_schedule (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void raw3215_next_io(struct raw3215_info *raw, struct tty_struct *tty)
{
	raw3215_mk_write_req(raw);
	raw3215_try_io(raw);
	if (tty && RAW3215_BUFFER_SIZE - raw->count >= RAW3215_MIN_SPACE)
		tasklet_schedule(&raw->tlet);
}