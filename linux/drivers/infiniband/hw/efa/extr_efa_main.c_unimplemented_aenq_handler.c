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
struct efa_dev {int /*<<< orphan*/  ibdev; } ;
struct efa_admin_aenq_entry {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ibdev_err (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static void unimplemented_aenq_handler(void *data,
				       struct efa_admin_aenq_entry *aenq_e)
{
	struct efa_dev *dev = (struct efa_dev *)data;

	ibdev_err(&dev->ibdev,
		  "Unknown event was received or event with unimplemented handler\n");
}