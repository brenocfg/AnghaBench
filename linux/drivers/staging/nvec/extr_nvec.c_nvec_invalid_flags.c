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
struct nvec_chip {scalar_t__ state; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,unsigned int,scalar_t__) ; 

__attribute__((used)) static void nvec_invalid_flags(struct nvec_chip *nvec, unsigned int status,
			       bool reset)
{
	dev_err(nvec->dev, "unexpected status flags 0x%02x during state %i\n",
		status, nvec->state);
	if (reset)
		nvec->state = 0;
}