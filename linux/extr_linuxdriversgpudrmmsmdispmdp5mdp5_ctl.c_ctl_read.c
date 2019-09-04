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
struct mdp5_kms {int dummy; } ;
struct mdp5_ctl {int /*<<< orphan*/  reg_offset; int /*<<< orphan*/  ctlm; } ;

/* Variables and functions */
 struct mdp5_kms* get_kms (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mdp5_read (struct mdp5_kms*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline
u32 ctl_read(struct mdp5_ctl *ctl, u32 reg)
{
	struct mdp5_kms *mdp5_kms = get_kms(ctl->ctlm);

	(void)ctl->reg_offset; /* TODO use this instead of mdp5_write */
	return mdp5_read(mdp5_kms, reg);
}