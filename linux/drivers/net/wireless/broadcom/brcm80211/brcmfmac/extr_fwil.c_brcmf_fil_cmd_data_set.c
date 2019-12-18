#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct brcmf_if {TYPE_1__* drvr; int /*<<< orphan*/  ifidx; } ;
typedef  int /*<<< orphan*/  s32 ;
struct TYPE_2__ {int /*<<< orphan*/  proto_block; } ;

/* Variables and functions */
 int /*<<< orphan*/  BRCMF_FIL_ON () ; 
 int /*<<< orphan*/  FIL ; 
 int /*<<< orphan*/  MAX_HEX_DUMP_LEN ; 
 int /*<<< orphan*/  brcmf_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  brcmf_dbg_hex_dump (int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  brcmf_fil_cmd_data (struct brcmf_if*,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  min_t (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uint ; 

s32
brcmf_fil_cmd_data_set(struct brcmf_if *ifp, u32 cmd, void *data, u32 len)
{
	s32 err;

	mutex_lock(&ifp->drvr->proto_block);

	brcmf_dbg(FIL, "ifidx=%d, cmd=%d, len=%d\n", ifp->ifidx, cmd, len);
	brcmf_dbg_hex_dump(BRCMF_FIL_ON(), data,
			   min_t(uint, len, MAX_HEX_DUMP_LEN), "data\n");

	err = brcmf_fil_cmd_data(ifp, cmd, data, len, true);
	mutex_unlock(&ifp->drvr->proto_block);

	return err;
}