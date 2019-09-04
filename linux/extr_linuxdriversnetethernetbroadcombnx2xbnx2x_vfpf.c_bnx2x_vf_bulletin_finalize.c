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
struct pf_vf_bulletin_content {int /*<<< orphan*/  crc; int /*<<< orphan*/  length; } ;

/* Variables and functions */
 int /*<<< orphan*/  BULLETIN_CONTENT_LEGACY_SIZE ; 
 int /*<<< orphan*/  BULLETIN_CONTENT_SIZE ; 
 int /*<<< orphan*/  bnx2x_crc_vf_bulletin (struct pf_vf_bulletin_content*) ; 

void bnx2x_vf_bulletin_finalize(struct pf_vf_bulletin_content *bulletin,
				bool support_long)
{
	/* Older VFs contain a bug where they can't check CRC for bulletin
	 * boards of length greater than legacy size.
	 */
	bulletin->length = support_long ? BULLETIN_CONTENT_SIZE :
					  BULLETIN_CONTENT_LEGACY_SIZE;
	bulletin->crc = bnx2x_crc_vf_bulletin(bulletin);
}