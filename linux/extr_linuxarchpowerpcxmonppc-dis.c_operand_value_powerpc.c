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
struct powerpc_operand {long (* extract ) (unsigned long,int /*<<< orphan*/ ,int*) ;unsigned long shift; unsigned long bitm; int flags; } ;
typedef  int /*<<< orphan*/  ppc_cpu_t ;

/* Variables and functions */
 int PPC_OPERAND_SIGNED ; 
 long stub1 (unsigned long,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static long
operand_value_powerpc (const struct powerpc_operand *operand,
		       unsigned long insn, ppc_cpu_t dialect)
{
  long value;
  int invalid;
  /* Extract the value from the instruction.  */
  if (operand->extract)
    value = (*operand->extract) (insn, dialect, &invalid);
  else
    {
      if (operand->shift >= 0)
	value = (insn >> operand->shift) & operand->bitm;
      else
	value = (insn << -operand->shift) & operand->bitm;
      if ((operand->flags & PPC_OPERAND_SIGNED) != 0)
	{
	  /* BITM is always some number of zeros followed by some
	     number of ones, followed by some number of zeros.  */
	  unsigned long top = operand->bitm;
	  /* top & -top gives the rightmost 1 bit, so this
	     fills in any trailing zeros.  */
	  top |= (top & -top) - 1;
	  top &= ~(top >> 1);
	  value = (value ^ top) - top;
	}
    }

  return value;
}