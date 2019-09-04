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
struct seqbuf {scalar_t__ pos; scalar_t__ buf; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (void*,scalar_t__,size_t) ; 
 size_t min (size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  seqbuf_avail (struct seqbuf*) ; 
 int seqbuf_status (struct seqbuf*) ; 

__attribute__((used)) static int seqbuf_read(struct seqbuf *seqbuf, void *buf, size_t nbyte)
{
	nbyte = min(nbyte, seqbuf_avail(seqbuf));
	memcpy(buf, seqbuf->buf + seqbuf->pos, nbyte);
	seqbuf->pos += nbyte;
	return seqbuf_status(seqbuf);
}