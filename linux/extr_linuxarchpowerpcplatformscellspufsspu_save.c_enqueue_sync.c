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
typedef  int /*<<< orphan*/  addr64 ;

/* Variables and functions */
 int /*<<< orphan*/  MFC_Cmd ; 
 int /*<<< orphan*/  MFC_TagID ; 
 int /*<<< orphan*/  spu_writech (int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static inline void enqueue_sync(addr64 lscsa_ea)
{
	unsigned int tag_id = 0;
	unsigned int cmd = 0xCC;

	/* Save, Step 14:
	 *    Enqueue an MFC_SYNC command (tag 0).
	 */
	spu_writech(MFC_TagID, tag_id);
	spu_writech(MFC_Cmd, cmd);
}