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
struct gc_pad {scalar_t__ type; } ;
struct gc {struct gc_pad* pads; } ;

/* Variables and functions */
 scalar_t__ GC_DDR ; 
 int GC_MAX_DEVICES ; 
 scalar_t__ GC_PSX ; 
 int GC_PSX_BYTES ; 
 int /*<<< orphan*/  gc_psx_read_packet (struct gc*,unsigned char**,unsigned char*) ; 
 int /*<<< orphan*/  gc_psx_report_one (struct gc_pad*,unsigned char,unsigned char*) ; 

__attribute__((used)) static void gc_psx_process_packet(struct gc *gc)
{
	unsigned char data[GC_MAX_DEVICES][GC_PSX_BYTES];
	unsigned char id[GC_MAX_DEVICES];
	struct gc_pad *pad;
	int i;

	gc_psx_read_packet(gc, data, id);

	for (i = 0; i < GC_MAX_DEVICES; i++) {
		pad = &gc->pads[i];
		if (pad->type == GC_PSX || pad->type == GC_DDR)
			gc_psx_report_one(pad, id[i], data[i]);
	}
}