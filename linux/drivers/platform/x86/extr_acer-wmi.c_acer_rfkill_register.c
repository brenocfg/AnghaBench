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
typedef  scalar_t__ u32 ;
struct rfkill {int dummy; } ;
struct device {int dummy; } ;
typedef  enum rfkill_type { ____Placeholder_rfkill_type } rfkill_type ;
typedef  int /*<<< orphan*/  acpi_status ;

/* Variables and functions */
 scalar_t__ ACPI_SUCCESS (int /*<<< orphan*/ ) ; 
 int ENOMEM ; 
 struct rfkill* ERR_PTR (int) ; 
 int /*<<< orphan*/  acer_rfkill_ops ; 
 int /*<<< orphan*/  get_u32 (scalar_t__*,scalar_t__) ; 
 struct rfkill* rfkill_alloc (char*,struct device*,int,int /*<<< orphan*/ *,void*) ; 
 int /*<<< orphan*/  rfkill_destroy (struct rfkill*) ; 
 int rfkill_register (struct rfkill*) ; 
 int /*<<< orphan*/  rfkill_set_sw_state (struct rfkill*,int) ; 

__attribute__((used)) static struct rfkill *acer_rfkill_register(struct device *dev,
					   enum rfkill_type type,
					   char *name, u32 cap)
{
	int err;
	struct rfkill *rfkill_dev;
	u32 state;
	acpi_status status;

	rfkill_dev = rfkill_alloc(name, dev, type,
				  &acer_rfkill_ops,
				  (void *)(unsigned long)cap);
	if (!rfkill_dev)
		return ERR_PTR(-ENOMEM);

	status = get_u32(&state, cap);

	err = rfkill_register(rfkill_dev);
	if (err) {
		rfkill_destroy(rfkill_dev);
		return ERR_PTR(err);
	}

	if (ACPI_SUCCESS(status))
		rfkill_set_sw_state(rfkill_dev, !state);

	return rfkill_dev;
}