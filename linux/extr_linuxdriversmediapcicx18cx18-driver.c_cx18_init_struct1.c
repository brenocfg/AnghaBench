#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_34__   TYPE_9__ ;
typedef  struct TYPE_33__   TYPE_8__ ;
typedef  struct TYPE_32__   TYPE_7__ ;
typedef  struct TYPE_31__   TYPE_6__ ;
typedef  struct TYPE_30__   TYPE_5__ ;
typedef  struct TYPE_29__   TYPE_4__ ;
typedef  struct TYPE_28__   TYPE_3__ ;
typedef  struct TYPE_27__   TYPE_2__ ;
typedef  struct TYPE_26__   TYPE_1__ ;
typedef  struct TYPE_25__   TYPE_17__ ;
typedef  struct TYPE_24__   TYPE_16__ ;
typedef  struct TYPE_23__   TYPE_15__ ;
typedef  struct TYPE_22__   TYPE_14__ ;
typedef  struct TYPE_21__   TYPE_13__ ;
typedef  struct TYPE_20__   TYPE_12__ ;
typedef  struct TYPE_19__   TYPE_11__ ;
typedef  struct TYPE_18__   TYPE_10__ ;

/* Type definitions */
struct TYPE_23__ {int /*<<< orphan*/  buf_list; int /*<<< orphan*/  list; } ;
struct TYPE_22__ {int /*<<< orphan*/  list; } ;
struct TYPE_20__ {int /*<<< orphan*/  sliced; } ;
struct TYPE_21__ {TYPE_12__ fmt; int /*<<< orphan*/  type; } ;
struct TYPE_24__ {TYPE_15__ sliced_mpeg_mdl; TYPE_14__ sliced_mpeg_buf; TYPE_13__ in; int /*<<< orphan*/ * sliced_in; } ;
struct TYPE_25__ {int capabilities; TYPE_11__* video_median_filter_type; TYPE_9__* video_temporal_filter_mode; TYPE_7__* video_spatial_filter_mode; TYPE_5__* video_spatial_filter; TYPE_3__* video_temporal_filter; int /*<<< orphan*/  hdl; int /*<<< orphan*/ * priv; int /*<<< orphan*/  func; int /*<<< orphan*/ * ops; int /*<<< orphan*/  port; } ;
struct TYPE_26__ {int /*<<< orphan*/ * ctrl_handler; } ;
struct cx18 {int open_id; int filter_mode; TYPE_16__ vbi; int /*<<< orphan*/  dma_waitq; int /*<<< orphan*/  mb_cpu_waitq; int /*<<< orphan*/  mb_apu_waitq; int /*<<< orphan*/  cap_w; TYPE_17__ cxhdl; int /*<<< orphan*/  spatial_strength; int /*<<< orphan*/  temporal_strength; TYPE_1__ v4l2_dev; int /*<<< orphan*/ * streams; int /*<<< orphan*/  epu2cpu_mb_lock; int /*<<< orphan*/  epu2apu_mb_lock; int /*<<< orphan*/  gpio_lock; int /*<<< orphan*/  serialize_lock; int /*<<< orphan*/  pci_dev; int /*<<< orphan*/  base_addr; } ;
struct TYPE_33__ {int val; } ;
struct TYPE_34__ {TYPE_8__ cur; } ;
struct TYPE_31__ {int val; } ;
struct TYPE_32__ {TYPE_6__ cur; } ;
struct TYPE_29__ {int /*<<< orphan*/  val; } ;
struct TYPE_30__ {TYPE_4__ cur; } ;
struct TYPE_27__ {int /*<<< orphan*/  val; } ;
struct TYPE_28__ {TYPE_2__ cur; } ;
struct TYPE_18__ {int val; } ;
struct TYPE_19__ {TYPE_10__ cur; } ;

/* Variables and functions */
 size_t CX18_ENC_STREAM_TYPE_MPG ; 
 int CX2341X_CAP_HAS_SLICED_VBI ; 
 int CX2341X_CAP_HAS_TS ; 
 int /*<<< orphan*/  CX2341X_PORT_MEMORY ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  V4L2_BUF_TYPE_VBI_CAPTURE ; 
 int /*<<< orphan*/  cx18_api_func ; 
 int cx18_create_in_workq (struct cx18*) ; 
 int /*<<< orphan*/  cx18_cxhdl_ops ; 
 int /*<<< orphan*/  cx18_init_in_work_orders (struct cx18*) ; 
 int cx2341x_handler_init (TYPE_17__*,int) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pci_resource_start (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cx18_init_struct1(struct cx18 *cx)
{
	int ret;

	cx->base_addr = pci_resource_start(cx->pci_dev, 0);

	mutex_init(&cx->serialize_lock);
	mutex_init(&cx->gpio_lock);
	mutex_init(&cx->epu2apu_mb_lock);
	mutex_init(&cx->epu2cpu_mb_lock);

	ret = cx18_create_in_workq(cx);
	if (ret)
		return ret;

	cx18_init_in_work_orders(cx);

	/* start counting open_id at 1 */
	cx->open_id = 1;

	/* Initial settings */
	cx->cxhdl.port = CX2341X_PORT_MEMORY;
	cx->cxhdl.capabilities = CX2341X_CAP_HAS_TS | CX2341X_CAP_HAS_SLICED_VBI;
	cx->cxhdl.ops = &cx18_cxhdl_ops;
	cx->cxhdl.func = cx18_api_func;
	cx->cxhdl.priv = &cx->streams[CX18_ENC_STREAM_TYPE_MPG];
	ret = cx2341x_handler_init(&cx->cxhdl, 50);
	if (ret)
		return ret;
	cx->v4l2_dev.ctrl_handler = &cx->cxhdl.hdl;

	cx->temporal_strength = cx->cxhdl.video_temporal_filter->cur.val;
	cx->spatial_strength = cx->cxhdl.video_spatial_filter->cur.val;
	cx->filter_mode = cx->cxhdl.video_spatial_filter_mode->cur.val |
		(cx->cxhdl.video_temporal_filter_mode->cur.val << 1) |
		(cx->cxhdl.video_median_filter_type->cur.val << 2);

	init_waitqueue_head(&cx->cap_w);
	init_waitqueue_head(&cx->mb_apu_waitq);
	init_waitqueue_head(&cx->mb_cpu_waitq);
	init_waitqueue_head(&cx->dma_waitq);

	/* VBI */
	cx->vbi.in.type = V4L2_BUF_TYPE_VBI_CAPTURE;
	cx->vbi.sliced_in = &cx->vbi.in.fmt.sliced;

	/* IVTV style VBI insertion into MPEG streams */
	INIT_LIST_HEAD(&cx->vbi.sliced_mpeg_buf.list);
	INIT_LIST_HEAD(&cx->vbi.sliced_mpeg_mdl.list);
	INIT_LIST_HEAD(&cx->vbi.sliced_mpeg_mdl.buf_list);
	list_add(&cx->vbi.sliced_mpeg_buf.list,
		 &cx->vbi.sliced_mpeg_mdl.buf_list);
	return 0;
}