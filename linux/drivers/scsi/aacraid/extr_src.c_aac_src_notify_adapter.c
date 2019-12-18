#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct aac_dev {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  ODR_C; } ;

/* Variables and functions */
#define  AdapNormCmdQue 133 
#define  AdapNormRespQue 132 
#define  AdapPrintfDone 131 
 int /*<<< orphan*/  BUG () ; 
#define  FastIo 130 
#define  HostNormCmdNotFull 129 
#define  HostNormRespNotFull 128 
 int INBOUNDDOORBELL_1 ; 
 int INBOUNDDOORBELL_2 ; 
 int INBOUNDDOORBELL_3 ; 
 int INBOUNDDOORBELL_4 ; 
 int INBOUNDDOORBELL_5 ; 
 int INBOUNDDOORBELL_6 ; 
 TYPE_1__ MUnit ; 
 int SRC_ODR_SHIFT ; 
 int /*<<< orphan*/  src_writel (struct aac_dev*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void aac_src_notify_adapter(struct aac_dev *dev, u32 event)
{
	switch (event) {

	case AdapNormCmdQue:
		src_writel(dev, MUnit.ODR_C,
			INBOUNDDOORBELL_1 << SRC_ODR_SHIFT);
		break;
	case HostNormRespNotFull:
		src_writel(dev, MUnit.ODR_C,
			INBOUNDDOORBELL_4 << SRC_ODR_SHIFT);
		break;
	case AdapNormRespQue:
		src_writel(dev, MUnit.ODR_C,
			INBOUNDDOORBELL_2 << SRC_ODR_SHIFT);
		break;
	case HostNormCmdNotFull:
		src_writel(dev, MUnit.ODR_C,
			INBOUNDDOORBELL_3 << SRC_ODR_SHIFT);
		break;
	case FastIo:
		src_writel(dev, MUnit.ODR_C,
			INBOUNDDOORBELL_6 << SRC_ODR_SHIFT);
		break;
	case AdapPrintfDone:
		src_writel(dev, MUnit.ODR_C,
			INBOUNDDOORBELL_5 << SRC_ODR_SHIFT);
		break;
	default:
		BUG();
		break;
	}
}