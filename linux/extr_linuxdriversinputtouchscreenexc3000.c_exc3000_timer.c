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
struct timer_list {int dummy; } ;
struct exc3000_data {int /*<<< orphan*/  input; } ;

/* Variables and functions */
 struct exc3000_data* data ; 
 struct exc3000_data* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  input_mt_sync_frame (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  input_sync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  timer ; 

__attribute__((used)) static void exc3000_timer(struct timer_list *t)
{
	struct exc3000_data *data = from_timer(data, t, timer);

	input_mt_sync_frame(data->input);
	input_sync(data->input);
}