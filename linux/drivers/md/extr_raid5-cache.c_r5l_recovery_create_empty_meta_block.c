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
typedef  int /*<<< orphan*/  u64 ;
struct r5l_meta_block {void* position; void* seq; void* meta_size; int /*<<< orphan*/  version; void* magic; } ;
struct r5l_log {int dummy; } ;
struct page {int dummy; } ;
typedef  int /*<<< orphan*/  sector_t ;

/* Variables and functions */
 int R5LOG_MAGIC ; 
 int /*<<< orphan*/  R5LOG_VERSION ; 
 int /*<<< orphan*/  clear_page (struct r5l_meta_block*) ; 
 void* cpu_to_le32 (int) ; 
 void* cpu_to_le64 (int /*<<< orphan*/ ) ; 
 struct r5l_meta_block* page_address (struct page*) ; 

__attribute__((used)) static void
r5l_recovery_create_empty_meta_block(struct r5l_log *log,
				     struct page *page,
				     sector_t pos, u64 seq)
{
	struct r5l_meta_block *mb;

	mb = page_address(page);
	clear_page(mb);
	mb->magic = cpu_to_le32(R5LOG_MAGIC);
	mb->version = R5LOG_VERSION;
	mb->meta_size = cpu_to_le32(sizeof(struct r5l_meta_block));
	mb->seq = cpu_to_le64(seq);
	mb->position = cpu_to_le64(pos);
}