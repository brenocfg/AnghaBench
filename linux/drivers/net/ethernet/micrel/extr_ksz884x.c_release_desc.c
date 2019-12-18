#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int hw_owned; } ;
struct TYPE_13__ {scalar_t__ data; TYPE_5__ tx; } ;
struct TYPE_9__ {scalar_t__ data; } ;
struct TYPE_14__ {scalar_t__ buf_size; TYPE_6__ ctrl; TYPE_2__ buf; } ;
struct ksz_desc {TYPE_7__ sw; TYPE_4__* phw; } ;
struct TYPE_10__ {void* data; } ;
struct TYPE_8__ {void* data; } ;
struct TYPE_11__ {TYPE_3__ ctrl; TYPE_1__ buf; } ;

/* Variables and functions */
 void* cpu_to_le32 (scalar_t__) ; 

__attribute__((used)) static inline void release_desc(struct ksz_desc *desc)
{
	desc->sw.ctrl.tx.hw_owned = 1;
	if (desc->sw.buf_size != desc->sw.buf.data) {
		desc->sw.buf_size = desc->sw.buf.data;
		desc->phw->buf.data = cpu_to_le32(desc->sw.buf.data);
	}
	desc->phw->ctrl.data = cpu_to_le32(desc->sw.ctrl.data);
}