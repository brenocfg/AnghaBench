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
typedef  int u32 ;

/* Variables and functions */
 int MBI_ENABLE ; 

__attribute__((used)) static inline u32 iosf_mbi_form_mcr(u8 op, u8 port, u8 offset)
{
	return (op << 24) | (port << 16) | (offset << 8) | MBI_ENABLE;
}