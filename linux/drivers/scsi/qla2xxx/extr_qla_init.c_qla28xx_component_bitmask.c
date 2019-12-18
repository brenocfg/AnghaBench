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
typedef  int uint ;
struct qla27xx_image_status {int bitmap; } ;

/* Variables and functions */
 int QLA27XX_PRIMARY_IMAGE ; 
 int QLA27XX_SECONDARY_IMAGE ; 

__attribute__((used)) static inline uint
qla28xx_component_bitmask(struct qla27xx_image_status *aux, uint bitmask)
{
	return aux->bitmap & bitmask ?
	    QLA27XX_SECONDARY_IMAGE : QLA27XX_PRIMARY_IMAGE;
}