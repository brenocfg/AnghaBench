#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  PVIO; } ;
struct riva_par {TYPE_1__ riva; } ;

/* Variables and functions */
 unsigned char VGA_RD08 (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline unsigned char MISCin(struct riva_par *par)
{
	return (VGA_RD08(par->riva.PVIO, 0x3cc));
}