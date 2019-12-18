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
struct stripe_head {int dummy; } ;
struct ppl_log {struct ppl_conf* ppl_conf; } ;
struct ppl_io_unit {int /*<<< orphan*/  seq; struct page* header_page; int /*<<< orphan*/  biovec; int /*<<< orphan*/  bio; int /*<<< orphan*/  pending_flushes; int /*<<< orphan*/  pending_stripes; int /*<<< orphan*/  stripe_list; int /*<<< orphan*/  log_sibling; struct ppl_log* log; } ;
struct ppl_header {int /*<<< orphan*/  generation; int /*<<< orphan*/  signature; struct ppl_io_unit* reserved; } ;
struct ppl_conf {int /*<<< orphan*/  seq; int /*<<< orphan*/  signature; int /*<<< orphan*/  io_pool; } ;
struct page {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_NOWAIT ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int PPL_HDR_RESERVED ; 
 int /*<<< orphan*/  PPL_IO_INLINE_BVECS ; 
 int /*<<< orphan*/  atomic64_add_return (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bio_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clear_page (struct ppl_header*) ; 
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_le64 (int /*<<< orphan*/ ) ; 
 struct ppl_io_unit* mempool_alloc (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct ppl_io_unit*,int,int) ; 
 struct ppl_header* page_address (struct page*) ; 

__attribute__((used)) static struct ppl_io_unit *ppl_new_iounit(struct ppl_log *log,
					  struct stripe_head *sh)
{
	struct ppl_conf *ppl_conf = log->ppl_conf;
	struct ppl_io_unit *io;
	struct ppl_header *pplhdr;
	struct page *header_page;

	io = mempool_alloc(&ppl_conf->io_pool, GFP_NOWAIT);
	if (!io)
		return NULL;

	header_page = io->header_page;
	memset(io, 0, sizeof(*io));
	io->header_page = header_page;

	io->log = log;
	INIT_LIST_HEAD(&io->log_sibling);
	INIT_LIST_HEAD(&io->stripe_list);
	atomic_set(&io->pending_stripes, 0);
	atomic_set(&io->pending_flushes, 0);
	bio_init(&io->bio, io->biovec, PPL_IO_INLINE_BVECS);

	pplhdr = page_address(io->header_page);
	clear_page(pplhdr);
	memset(pplhdr->reserved, 0xff, PPL_HDR_RESERVED);
	pplhdr->signature = cpu_to_le32(ppl_conf->signature);

	io->seq = atomic64_add_return(1, &ppl_conf->seq);
	pplhdr->generation = cpu_to_le64(io->seq);

	return io;
}