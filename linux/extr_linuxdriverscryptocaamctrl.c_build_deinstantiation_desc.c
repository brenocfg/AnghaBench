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

/* Variables and functions */
 int JUMP_CLASS_CLASS1 ; 
 int JUMP_TYPE_HALT ; 
 int OP_ALG_AAI_SHIFT ; 
 int OP_ALG_ALGSEL_RNG ; 
 int OP_ALG_AS_INITFINAL ; 
 int OP_TYPE_CLASS1_ALG ; 
 int /*<<< orphan*/  append_jump (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  append_operation (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  init_job_desc (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void build_deinstantiation_desc(u32 *desc, int handle)
{
	init_job_desc(desc, 0);

	/* Uninstantiate State Handle 0 */
	append_operation(desc, OP_TYPE_CLASS1_ALG | OP_ALG_ALGSEL_RNG |
			 (handle << OP_ALG_AAI_SHIFT) | OP_ALG_AS_INITFINAL);

	append_jump(desc, JUMP_CLASS_CLASS1 | JUMP_TYPE_HALT);
}