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
struct smscore_device_t {int /*<<< orphan*/  buffer_mng_waitq; } ;
struct smscore_buffer_t {int dummy; } ;

/* Variables and functions */
 struct smscore_buffer_t* get_entry (struct smscore_device_t*) ; 
 int /*<<< orphan*/  wait_event (int /*<<< orphan*/ ,struct smscore_buffer_t*) ; 

struct smscore_buffer_t *smscore_getbuffer(struct smscore_device_t *coredev)
{
	struct smscore_buffer_t *cb = NULL;

	wait_event(coredev->buffer_mng_waitq, (cb = get_entry(coredev)));

	return cb;
}