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
typedef  int ppc_cpu_t ;

/* Variables and functions */
 int ISA_V2 ; 
 scalar_t__ PPC_OPCODE_ANY ; 
 int valid_bo_post_v2 (long) ; 
 int valid_bo_pre_v2 (long) ; 

__attribute__((used)) static int
valid_bo (long value, ppc_cpu_t dialect, int extract)
{
  int valid_y = valid_bo_pre_v2 (value);
  int valid_at = valid_bo_post_v2 (value);

  /* When disassembling with -Many, accept either encoding on the
     second pass through opcodes.  */
  if (extract && dialect == ~(ppc_cpu_t) PPC_OPCODE_ANY)
    return valid_y || valid_at;
  if ((dialect & ISA_V2) == 0)
    return valid_y;
  else
    return valid_at;
}