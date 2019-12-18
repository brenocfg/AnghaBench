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
struct mal_instance {int /*<<< orphan*/  dcr_host; } ;

/* Variables and functions */
 int /*<<< orphan*/  dcr_read (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline u32 get_mal_dcrn(struct mal_instance *mal, int reg)
{
	return dcr_read(mal->dcr_host, reg);
}