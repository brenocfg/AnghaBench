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
struct seqbuf {char* buf; int pos; } ;

/* Variables and functions */
 int /*<<< orphan*/  seqbuf_avail (struct seqbuf*) ; 
 int seqbuf_status (struct seqbuf*) ; 
 int strnlen (char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int seqbuf_read_str(struct seqbuf *seqbuf, const char **str)
{
	*str = seqbuf->buf + seqbuf->pos;
	seqbuf->pos += strnlen(*str, seqbuf_avail(seqbuf));
	seqbuf->pos++;
	return seqbuf_status(seqbuf);
}