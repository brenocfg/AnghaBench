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
typedef  int /*<<< orphan*/  u8 ;
struct rtl_tcb_desc {int* empkt_len; int /*<<< orphan*/  empkt_num; } ;

/* Variables and functions */
 int /*<<< orphan*/  SET_EARLYMODE_LEN0 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  SET_EARLYMODE_LEN1 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  SET_EARLYMODE_LEN2_1 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  SET_EARLYMODE_LEN2_2 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  SET_EARLYMODE_LEN3 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  SET_EARLYMODE_LEN4 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  SET_EARLYMODE_PKTNUM (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void _rtl92de_insert_emcontent(struct rtl_tcb_desc *ptcb_desc,
				      u8 *virtualaddress)
{
	memset(virtualaddress, 0, 8);

	SET_EARLYMODE_PKTNUM(virtualaddress, ptcb_desc->empkt_num);
	SET_EARLYMODE_LEN0(virtualaddress, ptcb_desc->empkt_len[0]);
	SET_EARLYMODE_LEN1(virtualaddress, ptcb_desc->empkt_len[1]);
	SET_EARLYMODE_LEN2_1(virtualaddress, ptcb_desc->empkt_len[2] & 0xF);
	SET_EARLYMODE_LEN2_2(virtualaddress, ptcb_desc->empkt_len[2] >> 4);
	SET_EARLYMODE_LEN3(virtualaddress, ptcb_desc->empkt_len[3]);
	SET_EARLYMODE_LEN4(virtualaddress, ptcb_desc->empkt_len[4]);
}