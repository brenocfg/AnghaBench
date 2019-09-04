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
struct powerpc_operand {int flags; long shift; } ;

/* Variables and functions */
 int PPC_OPERAND_OPTIONAL_VALUE ; 

__attribute__((used)) static inline long
ppc_optional_operand_value (const struct powerpc_operand *operand)
{
  if ((operand->flags & PPC_OPERAND_OPTIONAL_VALUE) != 0)
    return (operand+1)->shift;
  return 0;
}