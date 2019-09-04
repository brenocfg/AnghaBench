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
typedef  int /*<<< orphan*/  u32 ;
struct hnae3_handle {int dummy; } ;
struct hclge_vport {int /*<<< orphan*/ * rss_indirection_tbl; int /*<<< orphan*/  rss_hash_key; int /*<<< orphan*/  rss_algo; } ;

/* Variables and functions */
 int HCLGE_RSS_IND_TBL_SIZE ; 
 int /*<<< orphan*/  HCLGE_RSS_KEY_SIZE ; 
 struct hclge_vport* hclge_get_vport (struct hnae3_handle*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int hclge_get_rss(struct hnae3_handle *handle, u32 *indir,
			 u8 *key, u8 *hfunc)
{
	struct hclge_vport *vport = hclge_get_vport(handle);
	int i;

	/* Get hash algorithm */
	if (hfunc)
		*hfunc = vport->rss_algo;

	/* Get the RSS Key required by the user */
	if (key)
		memcpy(key, vport->rss_hash_key, HCLGE_RSS_KEY_SIZE);

	/* Get indirect table */
	if (indir)
		for (i = 0; i < HCLGE_RSS_IND_TBL_SIZE; i++)
			indir[i] =  vport->rss_indirection_tbl[i];

	return 0;
}