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
struct komeda_pipeline {int /*<<< orphan*/  ctrlr; int /*<<< orphan*/  improc; int /*<<< orphan*/  merger; int /*<<< orphan*/  splitter; int /*<<< orphan*/ * scalers; int /*<<< orphan*/  compiz; int /*<<< orphan*/  wb_layer; int /*<<< orphan*/ * layers; struct komeda_dev* mdev; } ;
struct komeda_dev {struct komeda_pipeline** pipelines; } ;
struct komeda_component {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*,int) ; 
#define  KOMEDA_COMPONENT_COMPIZ0 141 
#define  KOMEDA_COMPONENT_COMPIZ1 140 
#define  KOMEDA_COMPONENT_IPS0 139 
#define  KOMEDA_COMPONENT_IPS1 138 
#define  KOMEDA_COMPONENT_LAYER0 137 
#define  KOMEDA_COMPONENT_LAYER1 136 
#define  KOMEDA_COMPONENT_LAYER2 135 
#define  KOMEDA_COMPONENT_LAYER3 134 
#define  KOMEDA_COMPONENT_MERGER 133 
#define  KOMEDA_COMPONENT_SCALER0 132 
#define  KOMEDA_COMPONENT_SCALER1 131 
#define  KOMEDA_COMPONENT_SPLITTER 130 
#define  KOMEDA_COMPONENT_TIMING_CTRLR 129 
#define  KOMEDA_COMPONENT_WB_LAYER 128 
 struct komeda_component** to_cpos (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct komeda_component **
komeda_pipeline_get_component_pos(struct komeda_pipeline *pipe, int id)
{
	struct komeda_dev *mdev = pipe->mdev;
	struct komeda_pipeline *temp = NULL;
	struct komeda_component **pos = NULL;

	switch (id) {
	case KOMEDA_COMPONENT_LAYER0:
	case KOMEDA_COMPONENT_LAYER1:
	case KOMEDA_COMPONENT_LAYER2:
	case KOMEDA_COMPONENT_LAYER3:
		pos = to_cpos(pipe->layers[id - KOMEDA_COMPONENT_LAYER0]);
		break;
	case KOMEDA_COMPONENT_WB_LAYER:
		pos = to_cpos(pipe->wb_layer);
		break;
	case KOMEDA_COMPONENT_COMPIZ0:
	case KOMEDA_COMPONENT_COMPIZ1:
		temp = mdev->pipelines[id - KOMEDA_COMPONENT_COMPIZ0];
		if (!temp) {
			DRM_ERROR("compiz-%d doesn't exist.\n", id);
			return NULL;
		}
		pos = to_cpos(temp->compiz);
		break;
	case KOMEDA_COMPONENT_SCALER0:
	case KOMEDA_COMPONENT_SCALER1:
		pos = to_cpos(pipe->scalers[id - KOMEDA_COMPONENT_SCALER0]);
		break;
	case KOMEDA_COMPONENT_SPLITTER:
		pos = to_cpos(pipe->splitter);
		break;
	case KOMEDA_COMPONENT_MERGER:
		pos = to_cpos(pipe->merger);
		break;
	case KOMEDA_COMPONENT_IPS0:
	case KOMEDA_COMPONENT_IPS1:
		temp = mdev->pipelines[id - KOMEDA_COMPONENT_IPS0];
		if (!temp) {
			DRM_ERROR("ips-%d doesn't exist.\n", id);
			return NULL;
		}
		pos = to_cpos(temp->improc);
		break;
	case KOMEDA_COMPONENT_TIMING_CTRLR:
		pos = to_cpos(pipe->ctrlr);
		break;
	default:
		pos = NULL;
		DRM_ERROR("Unknown pipeline resource ID: %d.\n", id);
		break;
	}

	return pos;
}