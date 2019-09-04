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
typedef  int u8 ;
struct acpi_ec {int /*<<< orphan*/  command_addr; } ;

/* Variables and functions */
 int ACPI_EC_FLAG_BURST ; 
 int ACPI_EC_FLAG_CMD ; 
 int ACPI_EC_FLAG_IBF ; 
 int ACPI_EC_FLAG_OBF ; 
 int ACPI_EC_FLAG_SCI ; 
 int /*<<< orphan*/  ec_dbg_raw (char*,int,int,int,int,int,int) ; 
 int inb (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline u8 acpi_ec_read_status(struct acpi_ec *ec)
{
	u8 x = inb(ec->command_addr);

	ec_dbg_raw("EC_SC(R) = 0x%2.2x "
		   "SCI_EVT=%d BURST=%d CMD=%d IBF=%d OBF=%d",
		   x,
		   !!(x & ACPI_EC_FLAG_SCI),
		   !!(x & ACPI_EC_FLAG_BURST),
		   !!(x & ACPI_EC_FLAG_CMD),
		   !!(x & ACPI_EC_FLAG_IBF),
		   !!(x & ACPI_EC_FLAG_OBF));
	return x;
}