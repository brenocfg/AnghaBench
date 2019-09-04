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
struct cc_hw_desc {int /*<<< orphan*/ * word; } ;
typedef  enum cc_setup_op { ____Placeholder_cc_setup_op } cc_setup_op ;

/* Variables and functions */
 int /*<<< orphan*/  FIELD_PREP (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  WORD4_SETUP_OPERATION ; 

__attribute__((used)) static inline void set_setup_mode(struct cc_hw_desc *pdesc,
				  enum cc_setup_op mode)
{
	pdesc->word[4] |= FIELD_PREP(WORD4_SETUP_OPERATION, mode);
}