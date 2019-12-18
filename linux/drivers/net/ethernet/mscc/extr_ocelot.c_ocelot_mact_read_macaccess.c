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
typedef  int /*<<< orphan*/  u32 ;
struct ocelot {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ANA_TABLES_MACACCESS ; 
 int /*<<< orphan*/  ocelot_read (struct ocelot*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline u32 ocelot_mact_read_macaccess(struct ocelot *ocelot)
{
	return ocelot_read(ocelot, ANA_TABLES_MACACCESS);
}