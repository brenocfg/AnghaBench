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
struct pblk {int dummy; } ;
struct line_header {scalar_t__ version_major; scalar_t__ version_minor; } ;
struct line_emeta {struct line_header header; } ;

/* Variables and functions */
 scalar_t__ EMETA_VERSION_MAJOR ; 
 scalar_t__ EMETA_VERSION_MINOR ; 
 int /*<<< orphan*/  pblk_err (struct pblk*,char*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  pblk_info (struct pblk*,char*,scalar_t__) ; 

__attribute__((used)) static int pblk_recov_check_line_version(struct pblk *pblk,
					 struct line_emeta *emeta)
{
	struct line_header *header = &emeta->header;

	if (header->version_major != EMETA_VERSION_MAJOR) {
		pblk_err(pblk, "line major version mismatch: %d, expected: %d\n",
			 header->version_major, EMETA_VERSION_MAJOR);
		return 1;
	}

#ifdef CONFIG_NVM_PBLK_DEBUG
	if (header->version_minor > EMETA_VERSION_MINOR)
		pblk_info(pblk, "newer line minor version found: %d\n",
				header->version_minor);
#endif

	return 0;
}