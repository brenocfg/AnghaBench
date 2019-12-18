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
struct lcs_card {int /*<<< orphan*/  ipm_list; int /*<<< orphan*/  read; int /*<<< orphan*/  write; int /*<<< orphan*/  lancmd_timeout; scalar_t__ pkt_seq; int /*<<< orphan*/  lan_type; } ;

/* Variables and functions */
 int GFP_DMA ; 
 int GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LCS_DBF_HEX (int,int /*<<< orphan*/ ,struct lcs_card**,int) ; 
 int /*<<< orphan*/  LCS_DBF_TEXT (int,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  LCS_FRAME_TYPE_AUTO ; 
 int /*<<< orphan*/  LCS_LANCMD_TIMEOUT_DEFAULT ; 
 struct lcs_card* kzalloc (int,int) ; 
 int lcs_alloc_channel (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lcs_cleanup_channel (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lcs_free_card (struct lcs_card*) ; 
 int /*<<< orphan*/  setup ; 

__attribute__((used)) static struct lcs_card *
lcs_alloc_card(void)
{
	struct lcs_card *card;
	int rc;

	LCS_DBF_TEXT(2, setup, "alloclcs");

	card = kzalloc(sizeof(struct lcs_card), GFP_KERNEL | GFP_DMA);
	if (card == NULL)
		return NULL;
	card->lan_type = LCS_FRAME_TYPE_AUTO;
	card->pkt_seq = 0;
	card->lancmd_timeout = LCS_LANCMD_TIMEOUT_DEFAULT;
	/* Allocate io buffers for the read channel. */
	rc = lcs_alloc_channel(&card->read);
	if (rc){
		LCS_DBF_TEXT(2, setup, "iccwerr");
		lcs_free_card(card);
		return NULL;
	}
	/* Allocate io buffers for the write channel. */
	rc = lcs_alloc_channel(&card->write);
	if (rc) {
		LCS_DBF_TEXT(2, setup, "iccwerr");
		lcs_cleanup_channel(&card->read);
		lcs_free_card(card);
		return NULL;
	}

#ifdef CONFIG_IP_MULTICAST
	INIT_LIST_HEAD(&card->ipm_list);
#endif
	LCS_DBF_HEX(2, setup, &card, sizeof(void*));
	return card;
}