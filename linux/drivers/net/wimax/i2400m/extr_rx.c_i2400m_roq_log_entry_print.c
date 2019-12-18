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
struct i2400m_roq_log_entry {int type; int /*<<< orphan*/  new_ws; int /*<<< orphan*/  nsn; int /*<<< orphan*/  sn; int /*<<< orphan*/  count; int /*<<< orphan*/  ws; } ;
struct i2400m {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
#define  I2400M_RO_TYPE_PACKET 131 
#define  I2400M_RO_TYPE_PACKET_WS 130 
#define  I2400M_RO_TYPE_RESET 129 
#define  I2400M_RO_TYPE_WS 128 
 int /*<<< orphan*/  dev_err (struct device*,char*,unsigned int,unsigned int,int,...) ; 
 struct device* i2400m_dev (struct i2400m*) ; 

__attribute__((used)) static
void i2400m_roq_log_entry_print(struct i2400m *i2400m, unsigned index,
				unsigned e_index,
				struct i2400m_roq_log_entry *e)
{
	struct device *dev = i2400m_dev(i2400m);

	switch(e->type) {
	case I2400M_RO_TYPE_RESET:
		dev_err(dev, "q#%d reset           ws %u cnt %u sn %u/%u"
			" - new nws %u\n",
			index, e->ws, e->count, e->sn, e->nsn, e->new_ws);
		break;
	case I2400M_RO_TYPE_PACKET:
		dev_err(dev, "q#%d queue           ws %u cnt %u sn %u/%u\n",
			index, e->ws, e->count, e->sn, e->nsn);
		break;
	case I2400M_RO_TYPE_WS:
		dev_err(dev, "q#%d update_ws       ws %u cnt %u sn %u/%u"
			" - new nws %u\n",
			index, e->ws, e->count, e->sn, e->nsn, e->new_ws);
		break;
	case I2400M_RO_TYPE_PACKET_WS:
		dev_err(dev, "q#%d queue_update_ws ws %u cnt %u sn %u/%u"
			" - new nws %u\n",
			index, e->ws, e->count, e->sn, e->nsn, e->new_ws);
		break;
	default:
		dev_err(dev, "q#%d BUG? entry %u - unknown type %u\n",
			index, e_index, e->type);
		break;
	}
}