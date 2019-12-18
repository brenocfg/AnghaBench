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
struct device {int dummy; } ;

/* Variables and functions */
 struct device* bus_find_next_device (int /*<<< orphan*/ *,struct device*) ; 
 int /*<<< orphan*/  put_device (struct device*) ; 
 int /*<<< orphan*/  scsi_bus_type ; 

__attribute__((used)) static inline struct device *next_scsi_device(struct device *start)
{
	struct device *next = bus_find_next_device(&scsi_bus_type, start);

	put_device(start);
	return next;
}