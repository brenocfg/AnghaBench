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
struct lcs_card {int /*<<< orphan*/  lan_type; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  LCS_DBF_TEXT (int,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  LCS_FRAME_TYPE_ENET ; 
 int /*<<< orphan*/  LCS_FRAME_TYPE_FDDI ; 
 int /*<<< orphan*/  LCS_INITIATOR_TCPIP ; 
 int lcs_send_startlan (struct lcs_card*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace ; 

__attribute__((used)) static int
lcs_startlan_auto(struct lcs_card *card)
{
	int rc;

	LCS_DBF_TEXT(2, trace, "strtauto");
#ifdef CONFIG_ETHERNET
	card->lan_type = LCS_FRAME_TYPE_ENET;
	rc = lcs_send_startlan(card, LCS_INITIATOR_TCPIP);
	if (rc == 0)
		return 0;

#endif
#ifdef CONFIG_FDDI
	card->lan_type = LCS_FRAME_TYPE_FDDI;
	rc = lcs_send_startlan(card, LCS_INITIATOR_TCPIP);
	if (rc == 0)
		return 0;
#endif
	return -EIO;
}