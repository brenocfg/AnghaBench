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
typedef  int u32 ;
typedef  int dma_addr_t ;
typedef  int /*<<< orphan*/  __le64 ;

/* Variables and functions */
 int /*<<< orphan*/  BUFDATALEN ; 
 int /*<<< orphan*/  DATAADDR ; 
 int SET_VAL (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  cpu_to_le64 (int) ; 

__attribute__((used)) static void xgene_set_addr_len(__le64 *desc, u32 idx, dma_addr_t addr, u32 len)
{
	desc[idx ^ 1] = cpu_to_le64(SET_VAL(DATAADDR, addr) |
				    SET_VAL(BUFDATALEN, len));
}