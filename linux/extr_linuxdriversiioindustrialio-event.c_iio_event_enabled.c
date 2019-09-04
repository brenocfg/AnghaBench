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
struct iio_event_interface {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  IIO_BUSY_BIT_POS ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

bool iio_event_enabled(const struct iio_event_interface *ev_int)
{
	return !!test_bit(IIO_BUSY_BIT_POS, &ev_int->flags);
}