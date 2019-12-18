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
typedef  int /*<<< orphan*/  wd33c93_regs ;
typedef  int uchar ;

/* Variables and functions */
 int ASR_DBR ; 
 int ASR_INT ; 
 int CTRL_EDI ; 
 int CTRL_IDI ; 
 int CTRL_POLLED ; 
 int WD_CMD_TRANS_INFO ; 
 int /*<<< orphan*/  WD_CONTROL ; 
 int /*<<< orphan*/  WD_DATA ; 
 int read_aux_stat (int /*<<< orphan*/  const) ; 
 int read_wd33c93 (int /*<<< orphan*/  const,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_wd33c93 (int /*<<< orphan*/  const,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  write_wd33c93_cmd (int /*<<< orphan*/  const,int) ; 

__attribute__((used)) static inline uchar
read_1_byte(const wd33c93_regs regs)
{
	uchar asr;
	uchar x = 0;

	write_wd33c93(regs, WD_CONTROL, CTRL_IDI | CTRL_EDI | CTRL_POLLED);
	write_wd33c93_cmd(regs, WD_CMD_TRANS_INFO | 0x80);
	do {
		asr = read_aux_stat(regs);
		if (asr & ASR_DBR)
			x = read_wd33c93(regs, WD_DATA);
	} while (!(asr & ASR_INT));
	return x;
}