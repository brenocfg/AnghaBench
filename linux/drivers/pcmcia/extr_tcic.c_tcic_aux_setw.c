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
typedef  int u_short ;
typedef  int u_char ;

/* Variables and functions */
 int /*<<< orphan*/  TCIC_AUX ; 
 int /*<<< orphan*/  TCIC_MODE ; 
 int TCIC_MODE_PGMMASK ; 
 int tcic_getb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tcic_setb (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  tcic_setw (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void tcic_aux_setw(u_short reg, u_short data)
{
    u_char mode = (tcic_getb(TCIC_MODE) & TCIC_MODE_PGMMASK) | reg;
    tcic_setb(TCIC_MODE, mode);
    tcic_setw(TCIC_AUX, data);
}