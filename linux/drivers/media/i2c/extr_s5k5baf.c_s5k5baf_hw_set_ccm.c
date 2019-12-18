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
typedef  int /*<<< orphan*/  u16 ;
struct s5k5baf {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  S5K5BAF_FW_ID_CCM ; 
 int /*<<< orphan*/ * s5k5baf_fw_get_seq (struct s5k5baf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  s5k5baf_write_nseq (struct s5k5baf*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void s5k5baf_hw_set_ccm(struct s5k5baf *state)
{
	u16 *seq = s5k5baf_fw_get_seq(state, S5K5BAF_FW_ID_CCM);

	if (seq)
		s5k5baf_write_nseq(state, seq);
}