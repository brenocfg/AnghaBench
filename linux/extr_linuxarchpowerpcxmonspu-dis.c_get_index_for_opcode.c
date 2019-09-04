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
struct spu_opcode {scalar_t__ insn_type; } ;

/* Variables and functions */
 scalar_t__ LBT ; 
 scalar_t__ RI10 ; 
 scalar_t__ RI16 ; 
 scalar_t__ RI18 ; 
 scalar_t__ RI8 ; 
 scalar_t__ RRR ; 
 int /*<<< orphan*/  init_spu_disassemble () ; 
 struct spu_opcode** spu_disassemble_table ; 

__attribute__((used)) static const struct spu_opcode *
get_index_for_opcode (unsigned int insn)
{
  const struct spu_opcode *index;
  unsigned int opcode = insn >> (32-11);

  /* Init the table.  This assumes that element 0/opcode 0 (currently
   * NOP) is always used */
  if (spu_disassemble_table[0] == 0)
    init_spu_disassemble ();

  if ((index = spu_disassemble_table[opcode & 0x780]) != 0
      && index->insn_type == RRR)
    return index;

  if ((index = spu_disassemble_table[opcode & 0x7f0]) != 0
      && (index->insn_type == RI18 || index->insn_type == LBT))
    return index;

  if ((index = spu_disassemble_table[opcode & 0x7f8]) != 0
      && index->insn_type == RI10)
    return index;

  if ((index = spu_disassemble_table[opcode & 0x7fc]) != 0
      && (index->insn_type == RI16))
    return index;

  if ((index = spu_disassemble_table[opcode & 0x7fe]) != 0
      && (index->insn_type == RI8))
    return index;

  if ((index = spu_disassemble_table[opcode & 0x7ff]) != 0)
    return index;

  return NULL;
}