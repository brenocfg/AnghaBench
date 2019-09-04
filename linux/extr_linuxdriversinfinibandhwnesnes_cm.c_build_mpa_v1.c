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
typedef  int u8 ;
struct nes_cm_node {int /*<<< orphan*/  mpa_frame_size; int /*<<< orphan*/  mpa_frame_rev; } ;
struct ietf_mpa_v1 {int /*<<< orphan*/  priv_data_len; int /*<<< orphan*/  rev; int /*<<< orphan*/  flags; int /*<<< orphan*/  key; } ;

/* Variables and functions */
 int /*<<< orphan*/  IEFT_MPA_KEY_REP ; 
 int /*<<< orphan*/  IEFT_MPA_KEY_REQ ; 
 int /*<<< orphan*/  IETF_MPA_FLAGS_CRC ; 
 int /*<<< orphan*/  IETF_MPA_KEY_SIZE ; 
#define  MPA_KEY_REPLY 129 
#define  MPA_KEY_REQUEST 128 
 int /*<<< orphan*/  htons (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void build_mpa_v1(struct nes_cm_node *cm_node, void *start_addr, u8 mpa_key)
{
	struct ietf_mpa_v1 *mpa_frame = (struct ietf_mpa_v1 *)start_addr;

	switch (mpa_key) {
	case MPA_KEY_REQUEST:
		memcpy(mpa_frame->key, IEFT_MPA_KEY_REQ, IETF_MPA_KEY_SIZE);
		break;
	case MPA_KEY_REPLY:
		memcpy(mpa_frame->key, IEFT_MPA_KEY_REP, IETF_MPA_KEY_SIZE);
		break;
	}
	mpa_frame->flags = IETF_MPA_FLAGS_CRC;
	mpa_frame->rev = cm_node->mpa_frame_rev;
	mpa_frame->priv_data_len = htons(cm_node->mpa_frame_size);
}