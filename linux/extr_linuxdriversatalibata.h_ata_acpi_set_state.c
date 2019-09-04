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
struct ata_port {int dummy; } ;
typedef  int /*<<< orphan*/  pm_message_t ;

/* Variables and functions */

__attribute__((used)) static inline void ata_acpi_set_state(struct ata_port *ap,
				      pm_message_t state) { }