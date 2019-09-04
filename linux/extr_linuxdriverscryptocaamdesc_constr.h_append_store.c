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
typedef  unsigned int u32 ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 unsigned int CMD_STORE ; 
 unsigned int LDST_SRCDST_MASK ; 
 unsigned int LDST_SRCDST_WORD_DESCBUF_JOB ; 
 unsigned int LDST_SRCDST_WORD_DESCBUF_JOB_WE ; 
 unsigned int LDST_SRCDST_WORD_DESCBUF_SHARED ; 
 unsigned int LDST_SRCDST_WORD_DESCBUF_SHARED_WE ; 
 int /*<<< orphan*/  append_cmd (unsigned int* const,unsigned int) ; 
 int /*<<< orphan*/  append_ptr (unsigned int* const,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void append_store(u32 * const desc, dma_addr_t ptr,
				unsigned int len, u32 options)
{
	u32 cmd_src;

	cmd_src = options & LDST_SRCDST_MASK;

	append_cmd(desc, CMD_STORE | options | len);

	/* The following options do not require pointer */
	if (!(cmd_src == LDST_SRCDST_WORD_DESCBUF_SHARED ||
	      cmd_src == LDST_SRCDST_WORD_DESCBUF_JOB    ||
	      cmd_src == LDST_SRCDST_WORD_DESCBUF_JOB_WE ||
	      cmd_src == LDST_SRCDST_WORD_DESCBUF_SHARED_WE))
		append_ptr(desc, ptr);
}