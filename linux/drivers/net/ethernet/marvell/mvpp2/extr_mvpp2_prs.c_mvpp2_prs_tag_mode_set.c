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
struct mvpp2 {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  MVPP2_PRS_DSA ; 
 int /*<<< orphan*/  MVPP2_PRS_EDSA ; 
 int /*<<< orphan*/  MVPP2_PRS_TAGGED ; 
 int /*<<< orphan*/  MVPP2_PRS_UNTAGGED ; 
#define  MVPP2_TAG_TYPE_DSA 131 
#define  MVPP2_TAG_TYPE_EDSA 130 
#define  MVPP2_TAG_TYPE_MH 129 
#define  MVPP2_TAG_TYPE_NONE 128 
 int /*<<< orphan*/  mvpp2_prs_dsa_tag_set (struct mvpp2*,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int mvpp2_prs_tag_mode_set(struct mvpp2 *priv, int port, int type)
{
	switch (type) {
	case MVPP2_TAG_TYPE_EDSA:
		/* Add port to EDSA entries */
		mvpp2_prs_dsa_tag_set(priv, port, true,
				      MVPP2_PRS_TAGGED, MVPP2_PRS_EDSA);
		mvpp2_prs_dsa_tag_set(priv, port, true,
				      MVPP2_PRS_UNTAGGED, MVPP2_PRS_EDSA);
		/* Remove port from DSA entries */
		mvpp2_prs_dsa_tag_set(priv, port, false,
				      MVPP2_PRS_TAGGED, MVPP2_PRS_DSA);
		mvpp2_prs_dsa_tag_set(priv, port, false,
				      MVPP2_PRS_UNTAGGED, MVPP2_PRS_DSA);
		break;

	case MVPP2_TAG_TYPE_DSA:
		/* Add port to DSA entries */
		mvpp2_prs_dsa_tag_set(priv, port, true,
				      MVPP2_PRS_TAGGED, MVPP2_PRS_DSA);
		mvpp2_prs_dsa_tag_set(priv, port, true,
				      MVPP2_PRS_UNTAGGED, MVPP2_PRS_DSA);
		/* Remove port from EDSA entries */
		mvpp2_prs_dsa_tag_set(priv, port, false,
				      MVPP2_PRS_TAGGED, MVPP2_PRS_EDSA);
		mvpp2_prs_dsa_tag_set(priv, port, false,
				      MVPP2_PRS_UNTAGGED, MVPP2_PRS_EDSA);
		break;

	case MVPP2_TAG_TYPE_MH:
	case MVPP2_TAG_TYPE_NONE:
		/* Remove port form EDSA and DSA entries */
		mvpp2_prs_dsa_tag_set(priv, port, false,
				      MVPP2_PRS_TAGGED, MVPP2_PRS_DSA);
		mvpp2_prs_dsa_tag_set(priv, port, false,
				      MVPP2_PRS_UNTAGGED, MVPP2_PRS_DSA);
		mvpp2_prs_dsa_tag_set(priv, port, false,
				      MVPP2_PRS_TAGGED, MVPP2_PRS_EDSA);
		mvpp2_prs_dsa_tag_set(priv, port, false,
				      MVPP2_PRS_UNTAGGED, MVPP2_PRS_EDSA);
		break;

	default:
		if ((type < 0) || (type > MVPP2_TAG_TYPE_EDSA))
			return -EINVAL;
	}

	return 0;
}